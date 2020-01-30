const $containers = document.querySelectorAll('.container');
const $element = document.querySelector('.element');

let $drag = null;

$element.addEventListener('dragstart', e => {
  $drag = this;
  console.log('dragstart');
});
$element.addEventListener('dragend', e => {
  console.log('dragend');
});

for (const $container of $containers) {
  $container.addEventListener('dragenter', e => {
    console.log('dragenter');
  });
  $container.addEventListener('dragleave', e => {
    console.log('dragleave');
  });
  $container.addEventListener('dragover', e => {
    e.preventDefault();
    console.log('dragover');
  });
  $container.addEventListener('drop', e => {
    e.target.append($drag);
    console.log('drop', $drag);
  });
}
